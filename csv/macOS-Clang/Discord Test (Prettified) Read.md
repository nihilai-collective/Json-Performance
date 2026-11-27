
----
### Discord Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1775.26 | 0.0754041 | 4626.02ms | 83958 | 4890 | 5.65587e+06 | 45102.4 | 0.0767479 | 1(Win) | true |
| simdjson (ondemand) | 1495.22 | 0.0487225 | 5577.22ms | 83958 | 30 | 20422 | 53549.9 | 0.0237728 | 2(Loss) | true |
