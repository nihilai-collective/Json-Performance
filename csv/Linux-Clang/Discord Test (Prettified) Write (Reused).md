
----
### Discord Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 18545.5 | 0.0303625 | 491.078ms | 94370 | 80 | 173.682 | 4852.84 | 0.102155 | 0.132764 | 1(Win) | true |
| Glaze | 3681.92 | 0.0938275 | 2519.57ms | 94370 | 1280 | 673268 | 24443.3 | 0.184917 | 0.671691 | 2(Loss) | true |
