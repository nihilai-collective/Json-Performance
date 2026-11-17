
----
### Discord Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2265.04 | 0.328616 | 353.868ms | 6701 | 2560 | 220063 | 2821.4 | 0.430548 | 1(Win) | true |
| Glaze | 2107.71 | 0.631588 | 364.403ms | 6701 | 640 | 234696 | 3032 | 0.905218 | 2(Loss) | true |
| Jsonifier (two-stage) | 1883.12 | 1.11225 | 430.264ms | 6701 | 1280 | 1.82363e+06 | 3393.6 | 2.90684 | 3(Loss) | true |
| simdjson (reflection) | 1629.58 | 0.344503 | 500.657ms | 6701 | 640 | 116814 | 3921.6 | 2.64151 | 4(Loss) | true |
| simdjson (ondemand) | 1326.79 | 0.253316 | 527.245ms | 6701 | 4890 | 727962 | 4816.57 | 0.570387 | 5(Loss) | true |
