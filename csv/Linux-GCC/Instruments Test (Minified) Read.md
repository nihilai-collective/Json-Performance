
----
### Instruments Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1725.14 | 0.0580816 | 6081.56ms | 108313 | 4890 | 5.91424e+06 | 59876.5 | 0.00442482 | 1.43448 | 1(Win) | true |
| simdjson (ondemand) | 1706.52 | 0.257568 | 6085.82ms | 108313 | 80 | 1.94452e+06 | 60529.8 | 0.105353 | 1.45014 | 2(Loss) | true |
