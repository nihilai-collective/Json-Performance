
----
### Marine IK Small Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 5568.37 | 0.238126 | 445.749ms | 24893 | 30 | 3091.95 | 4263.33 | 0.078125 | 0.44132 | 1(Win) | true |
| Glaze | 3121.22 | 0.116852 | 752.418ms | 24579 | 30 | 2310.34 | 7510 | 0.0443656 | 0.788953 | 2(Loss) | true |
