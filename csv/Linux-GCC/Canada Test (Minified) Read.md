
----
### Canada Test (Minified) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 26194.6 | 0.0508559 | 8223.46ms | 2251027 | 4890 | 8.49434e+06 | 81953.8 | 0.102941 | 0.0944833 | 1(Win) | true |
| simdjson (stage-1) | 15958 | 0.132231 | 6927.92ms | 2251027 | 320 | 1.01255e+07 | 134524 | 0.149236 | 0.155109 | 2(Loss) | true |
