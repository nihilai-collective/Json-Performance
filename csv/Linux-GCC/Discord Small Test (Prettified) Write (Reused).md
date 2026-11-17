
----
### Discord Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 17395.6 | 0.0583751 | 42.8753ms | 7376 | 640 | 35.6616 | 404.373 | 0.0405556 | 0.132803 | 1(Win) | true |
| Glaze | 4360.43 | 0.0553031 | 167.313ms | 7376 | 160 | 127.351 | 1613.21 | 0.191023 | 0.558011 | 2(Loss) | true |
| simdjson (reflection) | 521.566 | 0.172369 | 1376.64ms | 7376 | 1280 | 691753 | 13486.9 | 0.0574418 | 4.73757 | 3(Loss) | true |
