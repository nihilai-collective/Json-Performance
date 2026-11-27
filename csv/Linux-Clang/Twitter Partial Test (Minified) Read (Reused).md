
----
### Twitter Partial Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 8545.09 | 0.0666826 | 6032.98ms | 466906 | 640 | 772735 | 52109 | 0.060892 | 0.591433 | 2.99791 | 0.413554 | 0.000911901 | 1.88408e-06 | 1.11104e-06 | 1(Win) | true |
| Jsonifier | 8503.94 | 0.0340051 | 6039.36ms | 466906 | 4890 | 1.5503e+06 | 52361.2 | 0.0906209 | 0.592778 | 2.99907 | 0.413777 | 0.000939981 | 4.24629e-06 | 3.24505e-06 | 2(Loss) | true |
| simdjson (ondemand) | 7030.01 | 0.0333712 | 7136.84ms | 466906 | 2560 | 1.14375e+06 | 63339.3 | 0.0806225 | 0.718543 | 3.43396 | 0.369445 | 0.000714284 | 1.95101e-06 | 8.95188e-07 | 3(Loss) | true |
| Glaze | 3437.13 | 0.0616464 | 7076.03ms | 466906 | 320 | 2.04095e+06 | 129549 | 0.068926 | 1.48174 | 5.69176 | 0.985533 | 0.0016122 | 2.24215e-06 | 9.50405e-07 | 4(Loss) | true |
