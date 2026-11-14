
----
### Github Events Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 16200 | 0.213832 | 472.158ms | 78778 | 4890 | 480880 | 4637.58 | 0.127517 | 1(Win) | true |
| Glaze | 3960.47 | 0.217989 | 1950.46ms | 78778 | 30 | 51298.9 | 18969.6 | 0.542741 | 2(Loss) | true |
| simdjson (reflection) | 404.884 | 0.0964937 | 9673.07ms | 78778 | 640 | 2.05176e+07 | 185556 | 0.242786 | 3(Loss) | true |
