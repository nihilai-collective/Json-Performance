
----
### Apache Builds Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 26471.3 | 0.0522411 | 346.912ms | 94653 | 30 | 95.2057 | 3410.03 | 0.0293166 | 0.0928071 | 1(Win) | true |
| simdjson (reflection) | 15311.5 | 0.0265119 | 611.373ms | 94653 | 30 | 73.2885 | 5895.43 | 0.0163996 | 0.160966 | 2(Loss) | true |
| Glaze | 6775.67 | 0.177697 | 1349.23ms | 94653 | 640 | 358677 | 13322.4 | 0.126992 | 0.364642 | 3(Loss) | true |
