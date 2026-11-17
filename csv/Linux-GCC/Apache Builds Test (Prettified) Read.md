
----
### Apache Builds Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1761.69 | 0.0727345 | 6740.37ms | 124597 | 4890 | 1.17692e+07 | 67449.4 | 0.155125 | 1.40479 | 1(Win) | true |
| simdjson (ondemand) | 1726.57 | 0.247338 | 6961.07ms | 124597 | 320 | 9.27214e+06 | 68821.6 | 0.329038 | 1.43342 | 2(Loss) | true |
