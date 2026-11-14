
----
### Github Events Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1467.57 | 0.193496 | 5035.21ms | 65103 | 1280 | 8.57751e+06 | 42306.1 | 0.579606 | 1(Win) | true |
| simdjson (ondemand) | 994.483 | 0.416568 | 7156.66ms | 65103 | 640 | 4.32873e+07 | 62431.5 | 0.203546 | 2(Loss) | true |
