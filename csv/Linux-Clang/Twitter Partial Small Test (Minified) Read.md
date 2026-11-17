
----
### Twitter Partial Small Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 5657.75 | 0.329108 | 774.333ms | 2889 | 1280 | 3287.73 | 486.972 | 0.0115523 | 0.979802 | 3.75389 | 0.514365 | 0.000349926 | 3.10986e-05 | 3.78591e-06 | 1(Win) | true |
| simdjson (ondemand) STATISTICAL TIE | 5552.81 | 0.29089 | 772.857ms | 2889 | 40 | 83.3276 | 496.175 | 0.0218385 | 1.00031 | 3.78435 | 0.434406 | 0.00102111 | 0 | 0 | 2(Tie) | true |
| Jsonifier STATISTICAL TIE | 5547.5 | 0.193658 | 772.911ms | 2889 | 40 | 37.0026 | 496.65 | 0.31779 | 0.986033 | 3.75389 | 0.514365 | 0.000917272 | 3.46141e-05 | 0 | 2(Tie) | true |
| Glaze | 3151.28 | 0.121721 | 815.634ms | 2889 | 4890 | 5538.05 | 874.299 | 0.042297 | 1.70314 | 6.80547 | 1.23365 | 0.00035867 | 4.24004e-05 | 1.91121e-05 | 4(Loss) | true |
