
----
### Discord Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 15780.2 | 0.159104 | 343.871ms | 56369 | 4890 | 143657 | 3406.66 | 0.00987262 | 0.155641 | 1(Win) | true |
| simdjson (reflection) | 13756.4 | 0.0958426 | 391.862ms | 56369 | 30 | 420.833 | 3907.83 | 0.306983 | 0.17867 | 2(Loss) | true |
| Glaze | 5889.1 | 0.10159 | 916.458ms | 56369 | 4890 | 420529 | 9128.33 | 0.0671692 | 0.41915 | 3(Loss) | true |
