
----
### Discord Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1869.12 | 0.0315658 | 996.273ms | 4857 | 2560 | 1566.53 | 2478.17 | 0.0120254 | 2.80144 | 11.5985 | 2.21083 | 0.00218821 | 2.72641e-05 | 1.68893e-06 | 1(Win) | true |
| simdjson (ondemand) | 1601.42 | 0.0295162 | 1034.94ms | 4857 | 4890 | 3564.13 | 2892.42 | 0.0580448 | 3.26041 | 13.2351 | 2.12539 | 0.00143916 | 3.6041e-05 | 7.70503e-06 | 2(Loss) | true |
