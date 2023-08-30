FROM ghcr.io/omnetpp/omnetpp-gui:u22.05-6.0.1 as omnetpp

FROM omnetpp as inetbuilder
# Build INET
ARG VERSION=4.5.0
WORKDIR /root
RUN git clone --depth 1 --branch v$VERSION https://github.com/inet-framework/inet.git
WORKDIR /root/omnetpp
RUN . ./setenv && cd ../inet && . ./setenv && \
    make makefiles && \
    make -j $(nproc) MODE=release && \
    rm -rf out

# Build D6G
FROM inetbuilder as d6gbuilder
ARG VERSION=4.5.0
ARG OPP_VER=6.0.1
ENV OPP_VER=$VERSION
ENV INET_VER=$VERSION
COPY . /root/deterministic6g
WORKDIR /root/deterministic6g
RUN make makefiles && \
    make -j $(nproc) MODE=release && \
    rm -rf out

# second stage - copy only the final binaries (to get rid of the 'out' folder and reduce the image size)
FROM omnetpp

RUN mkdir -p /root/models/inet
WORKDIR /root/models/inet
COPY --from=inetbuilder /root/inet/ .

RUN mkdir -p /root/models/deterministic6g
WORKDIR /root/models/deterministic6g
COPY --from=d6gbuilder /root/deterministic6g/ .

WORKDIR /root/models
RUN chmod 777 /root/models
RUN /root/omnetpp/bin/omnetpp -nosplash -data /root/models -application org.eclipse.cdt.managedbuilder.core.headlessbuild -import /root/models/deterministic6g

ARG VERSION=4.5.0
ARG OPP_VER=6.0.1
ENV OPP_VER=$VERSION
ENV INET_VER=$VERSION
RUN echo 'PS1="inet-$INET_VER:\w\$ "' >> /root/.bashrc && \
    echo '[ -f "$HOME/omnetpp/setenv" ] && src "$HOME/omnetpp/setenv" -f' >> /root/.bashrc && \
    echo '[ -f "$HOME/models/inet/setenv" ] && src "$HOME/models/inet/setenv" -f' >> /root/.bashrc && \
    touch /root/.hushlogin
