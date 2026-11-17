
----
### Random Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 935.652 | 0.0449992 | 1264.27ms | 4926 | 1280 | 6534 | 5020.88 | 0.0075783 | 5.54661 | 24.701 | 4.90723 | 0.00990725 | 3.86977e-05 | 4.75792e-06 | 1(Win) | true |
| simdjson (ondemand) | 496.96 | 0.0367184 | 1708.13ms | 4926 | 2560 | 30842.8 | 9453.07 | 0.073691 | 10.4061 | 46.609 | 8.38104 | 0.0229492 | 8.82594e-05 | 3.96493e-05 | 2(Loss) | true |
