
----
### Apache Builds Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1690.97 | 0.287116 | 8492.68ms | 124597 | 160 | 6.51297e+06 | 70270.3 | 0.531186 | 1(Win) | true |
| simdjson (ondemand) | 1363.72 | 0.580853 | 5669.43ms | 124597 | 160 | 4.09844e+07 | 87133.1 | 0.36067 | 2(Loss) | true |
