
----
### Instruments Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 608.778 | 0.0258048 | 1455.89ms | 4669 | 2560 | 9119.48 | 7314.17 | 0.0393227 | 8.50558 | 37.8929 | 7.49754 | 0.0107663 | 4.25847e-05 | 1.15456e-05 | 1(Win) | true |
| simdjson (ondemand) | 249.453 | 0.0522768 | 2512.61ms | 4669 | 1280 | 111454 | 17849.9 | 0.0332965 | 20.6587 | 103.922 | 18.7734 | 0.0359313 | 3.86525e-05 | 5.18714e-06 | 2(Loss) | true |
