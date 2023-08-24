# Configuration file for the Sphinx documentation builder.
#
# For the full list of built-in configuration values, see the documentation:
# https://www.sphinx-doc.org/en/master/usage/configuration.html

# -- Path setup --------------------------------------------------------------

# If extensions (or modules to document with autodoc) are in another directory,
# add these directories to sys.path here. If the directory is relative to the
# documentation root, use os.path.abspath to make it absolute, like shown here.
#
# import os
# import sys
# import re
# sys.path.insert(0, os.path.abspath('.'))
# sys.path.insert(0, os.path.abspath('_themes'))

# -- Project information -----------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#project-information

project = 'Deterministic6G'
copyright = '2023, IPVS University of Stuttgart'
author = 'IPVS University of Stuttgart'

# -- General configuration ---------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#general-configuration
# extensions = []
extensions = ['breathe']

breathe_projects = {"Deterministic6G": "../doxy/xml"}
breathe_default_project = "Deterministic6G"

templates_path = ['_templates']
exclude_patterns = []



# -- Options for HTML output -------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#options-for-html-output

# html_theme_path = [os.path.abspath('source/_themes')]
html_theme = 'sphinxdoc'
html_static_path = ['_static']
