
----
### Discord Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 829.443 | 0.0474572 | 1307.1ms | 4857 | 320 | 2247.59 | 5584.47 | 0.0715201 | 6.25491 | 28.0819 | 5.48713 | 0.00624228 | 3.15267e-05 | 2.57361e-06 | 1(Win) | true |
| simdjson (ondemand) | 227.471 | 0.0281934 | 2790.99ms | 4857 | 2560 | 84376.3 | 20363 | 0.0324586 | 22.5438 | 113.57 | 21.8549 | 0.0436068 | 8.20337e-05 | 2.38058e-05 | 2(Loss) | true |
