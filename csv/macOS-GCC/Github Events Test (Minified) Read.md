
----
### Github Events Test (Minified) Read Results [(Here is the data we used for this test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1222.72 | 0.0976492 | 4428.49ms | 53331 | 1280 | 2.11179e+06 | 41596 | 0.0529177 | 1(Win) | true |
| simdjson (ondemand) | 799.771 | 0.117476 | 6396.1ms | 53331 | 2560 | 1.42878e+07 | 63593.7 | 0.473505 | 2(Loss) | true |
