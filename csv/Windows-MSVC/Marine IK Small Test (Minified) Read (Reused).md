
----
### Marine IK Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 641.903 | 0.333517 | 843.484ms | 4604 | 1280 | 666158 | 6840.16 | 0.245019 | 3.84055 | 1(Win) | true |
| Jsonifier (two-stage) | 562.822 | 0.0897575 | 967.991ms | 4604 | 80 | 3922.47 | 7801.25 | 0.0480461 | 4.38395 | 2(Loss) | true |
| simdjson (ondemand) | 199.966 | 0.214154 | 2341.95ms | 4604 | 1280 | 2.83022e+06 | 21957.3 | 0.338643 | 12.3648 | 3(Loss) | true |
| Glaze | 168.146 | 0.122766 | 2790.77ms | 4604 | 2560 | 2.63084e+06 | 26112.5 | 0.239623 | 14.7081 | 4(Loss) | true |
