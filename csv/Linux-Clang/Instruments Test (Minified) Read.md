
----
### Instruments Test (Minified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1739.32 | 0.229178 | 6006.96ms | 108313 | 160 | 2.96394e+06 | 59388.5 | 0.13632 | 1.4228 | 1(Win) | true |
| simdjson (ondemand) | 1580.1 | 0.0795022 | 6588.46ms | 108313 | 4890 | 1.32087e+07 | 65372.6 | 0.0399833 | 1.56621 | 2(Loss) | true |
