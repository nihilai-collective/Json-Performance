
----
### Canada Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2265.34 | 0.143896 | 569.77ms | 11579 | 4890 | 240594 | 4874.59 | 0.0209748 | 1.08695 | 1(Win) | true |
| Jsonifier | 2197.38 | 0.173037 | 586.829ms | 11579 | 2560 | 193575 | 5025.35 | 0.00838647 | 1.12095 | 2(Loss) | true |
| simdjson (ondemand) | 1978.07 | 0.143595 | 641.739ms | 11579 | 4890 | 314230 | 5582.5 | 0.179252 | 1.24538 | 3(Loss) | true |
| Glaze | 1859.41 | 0.10535 | 678.823ms | 11579 | 4890 | 191411 | 5938.75 | 0.0323303 | 1.32575 | 4(Loss) | true |
