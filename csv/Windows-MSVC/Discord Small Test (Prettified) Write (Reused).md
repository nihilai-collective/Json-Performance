
----
### Discord Small Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 8728.1 | 0.181623 | 85.0519ms | 7376 | 320 | 685.639 | 805.938 | 0.116189 | 0.274118 | 1(Win) | true |
| Glaze | 3344.36 | 0.158479 | 227.507ms | 7376 | 30 | 333.333 | 2103.33 | 0 | 0.727431 | 2(Loss) | true |
