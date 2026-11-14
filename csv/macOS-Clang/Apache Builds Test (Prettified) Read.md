
----
### Apache Builds Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1644.5 | 0.101922 | 7292.92ms | 124597 | 1280 | 6.94211e+06 | 72255.9 | 0.0580447 | 1(Win) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 1359.02 | 0.102541 | 8769.94ms | 124597 | 2560 | 2.05778e+07 | 87434.1 | 0.344786 | 2(Tie) | true |
| Glaze STATISTICAL TIE | 1358.42 | 0.0537449 | 8816.53ms | 124597 | 4890 | 1.08077e+07 | 87473.1 | 0.235904 | 2(Tie) | true |
| simdjson (ondemand) | 1112.02 | 0.0893346 | 5511.69ms | 124597 | 2560 | 2.33276e+07 | 106855 | 0.00488346 | 4(Loss) | true |
