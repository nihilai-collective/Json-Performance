
----
### Twitter Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 10032.5 | 0.30737 | 4557.8ms | 466906 | 80 | 1.48887e+06 | 44383.5 | 0.187837 | 0.246628 | 1(Win) | true |
| Jsonifier (two-stage) | 9695.3 | 0.233546 | 4510.27ms | 466906 | 4890 | 5.62591e+07 | 45927 | 0.0268481 | 0.255158 | 2(Loss) | true |
| simdjson (ondemand) | 7646.61 | 0.259298 | 6074.25ms | 466906 | 80 | 1.82394e+06 | 58231.9 | 0.0993313 | 0.323565 | 3(Loss) | true |
| Glaze | 3281.16 | 0.152601 | 6956.17ms | 466906 | 160 | 6.8618e+06 | 135707 | 0.026756 | 0.754385 | 4(Loss) | true |
