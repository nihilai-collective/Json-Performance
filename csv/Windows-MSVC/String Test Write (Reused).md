
----
### String Test Write (Reused) Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/String%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/String%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3432.01 | 0.304158 | 135.328ms | 4215 | 320 | 4061.13 | 1171.25 | 0.106838 | 0.705741 | 1(Win) | true |
| Glaze | 1762.14 | 0.397896 | 255.075ms | 4215 | 1280 | 105454 | 2281.17 | 0.00342466 | 1.38653 | 2(Loss) | true |
