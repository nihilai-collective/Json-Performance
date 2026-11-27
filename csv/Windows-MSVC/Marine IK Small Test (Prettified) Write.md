
----
### Marine IK Small Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 5159.22 | 0.211735 | 459.547ms | 24893 | 4890 | 464175 | 4601.43 | 0.238278 | 0.476675 | 1(Win) | true |
| Glaze | 2833.52 | 0.143442 | 839.895ms | 24579 | 4890 | 688551 | 8272.52 | 0.449365 | 0.870821 | 2(Loss) | true |
