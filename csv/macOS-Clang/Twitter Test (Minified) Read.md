
----
### Twitter Test (Minified) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 7446.92 | 0.103373 | 6044.11ms | 466906 | 1280 | 4.89026e+06 | 59793.3 | 0.0125952 | 1(Win) | true |
| simdjson (stage-1) | 6796.75 | 0.299571 | 6868.42ms | 466906 | 2560 | 9.86046e+07 | 65513.1 | 1.70441 | 2(Loss) | true |
