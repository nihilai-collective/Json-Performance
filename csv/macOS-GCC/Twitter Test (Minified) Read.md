
----
### Twitter Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1617.46 | 0.0830865 | 8060.97ms | 264040 | 640 | 1.07081e+07 | 155681 | 0.0523875 | 1(Win) | true |
| simdjson (ondemand) | 1291.74 | 0.211445 | 10037.9ms | 264040 | 320 | 5.43669e+07 | 194937 | 0.0619304 | 2(Loss) | true |
