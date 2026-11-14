
----
### Github Events Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1152.24 | 0.0279083 | 5705.34ms | 53331 | 2560 | 388489 | 44140.4 | 0.0234221 | 4.46017 | 17.1984 | 3.39203 | 0.0134824 | 3.1957e-05 | 1.78792e-05 | 1(Win) | true |
| simdjson (ondemand) | 481.43 | 0.145701 | 6069.36ms | 53331 | 320 | 7.58171e+06 | 105644 | 0.123036 | 10.6544 | 38.544 | 6.84824 | 0.0600383 | 8.32654e-05 | 2.85364e-05 | 2(Loss) | true |
