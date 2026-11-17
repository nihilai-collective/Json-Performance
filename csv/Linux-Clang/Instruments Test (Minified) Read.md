
----
### Instruments Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1641.9 | 0.725629 | 6415.06ms | 108313 | 30 | 6.25199e+06 | 62912.1 | 0.359993 | 1.50727 | 1(Win) | true |
| simdjson (ondemand) | 1503.83 | 0.0930175 | 6912.82ms | 108313 | 4890 | 1.9962e+07 | 68688.3 | 0.440284 | 1.64569 | 2(Loss) | true |
