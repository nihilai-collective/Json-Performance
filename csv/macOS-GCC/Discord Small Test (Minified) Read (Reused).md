
----
### Discord Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier STATISTICAL TIE | 2016.02 | 1.8692 | 326.64ms | 4857 | 640 | 1.18043e+06 | 2297.6 | 3.07121 | 1(Tie) | true |
| Glaze STATISTICAL TIE | 1962.71 | 1.17547 | 303.634ms | 4857 | 320 | 246261 | 2360 | 0.545331 | 1(Tie) | true |
| Jsonifier (two-stage) | 1370.41 | 1.06327 | 389.791ms | 4857 | 320 | 413308 | 3380 | 1.14647 | 3(Loss) | true |
| simdjson (ondemand) STATISTICAL TIE | 1129.42 | 0.269225 | 479.225ms | 4857 | 1280 | 156050 | 4101.2 | 0.39829 | 4(Tie) | true |
| simdjson (reflection) STATISTICAL TIE | 1127.79 | 0.309763 | 457.823ms | 4857 | 4890 | 791495 | 4107.15 | 0.987237 | 4(Tie) | true |
