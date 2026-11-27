
----
### Discord Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2742.26 | 0.0357116 | 3143.13ms | 83958 | 40 | 4348.97 | 29198 | 0.0553425 | 1(Win) | true |
| Jsonifier (two-stage) | 2496.39 | 0.051289 | 3405.71ms | 83958 | 4890 | 1.3233e+06 | 32073.8 | 0.0483041 | 2(Loss) | true |
| Glaze | 2164.48 | 0.116613 | 3841.89ms | 83958 | 1280 | 2.38188e+06 | 36992 | 0.0619393 | 3(Loss) | true |
| simdjson (ondemand) | 1204.58 | 0.048016 | 6992.16ms | 83958 | 4890 | 4.98123e+06 | 66470.3 | 0.912135 | 4(Loss) | true |
