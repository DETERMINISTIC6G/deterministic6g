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
COPY . /root/deterministic6g
WORKDIR /root/deterministic6g
RUN make makefiles && \
    make -j $(nproc) MODE=release && \
    rm -rf out

# second stage - copy only the final binaries (to get rid of the 'out' folder and reduce the image size)
FROM omnetpp
RUN mkdir -p /root/inet
WORKDIR /root/inet
COPY --from=inetbuilder /root/inet/ .
RUN mkdir -p /root/deterministic6g
COPY --from=d6gbuilder /root/deterministic6g/ .
ARG VERSION=4.5.0
ENV INET_VER=$VERSION
RUN echo 'PS1="inet-$INET_VER:\w\$ "' >> /root/.bashrc && \
    echo '[ -f "$HOME/omnetpp/setenv" ] && source "$HOME/omnetpp/setenv" -f' >> /root/.bashrc && \
    echo '[ -f "$HOME/inet/setenv" ] && source "$HOME/inet/setenv" -f' >> /root/.bashrc && \
    touch /root/.hushlogin