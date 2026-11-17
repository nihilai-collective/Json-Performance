
----
### Twitter Test (Minified) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 22644.7 | 0.0949916 | 1984.81ms | 466906 | 4890 | 1.7061e+06 | 19663.6 | 0.376537 | 0.109175 | 1(Win) | true |
| simdjson (stage-1) | 17025.5 | 0.0625946 | 2600.86ms | 466906 | 4890 | 1.31051e+06 | 26153.4 | 0.0196279 | 0.145268 | 2(Loss) | true |
