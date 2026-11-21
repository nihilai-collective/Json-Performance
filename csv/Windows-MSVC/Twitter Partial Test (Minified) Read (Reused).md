
----
### Twitter Partial Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 8422.08 | 0.114668 | 5492.9ms | 466906 | 2560 | 9.40906e+06 | 52870.1 | 0.0330891 | 0.293807 | 1(Win) | true |
| Jsonifier (two-stage) | 8330.2 | 0.143531 | 5543.46ms | 466906 | 2560 | 1.50689e+07 | 53453.3 | 0.0279235 | 0.297056 | 2(Loss) | true |
| simdjson (ondemand) | 4203.16 | 0.114657 | 5600.11ms | 466906 | 1280 | 1.8885e+07 | 105939 | 0.259719 | 0.588873 | 3(Loss) | true |
| Glaze | 2967.75 | 0.25244 | 7989.91ms | 466906 | 160 | 2.29529e+07 | 150038 | 0.0437198 | 0.834103 | 4(Loss) | true |
