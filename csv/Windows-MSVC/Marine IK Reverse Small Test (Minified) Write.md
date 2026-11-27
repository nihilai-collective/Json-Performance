
----
### Marine IK Reverse Small Test (Minified) Write Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1470.27 | 0.131965 | 331.539ms | 4918 | 80 | 1417.72 | 3190 | 0.156495 | 1.66767 | 1(Win) | true |
| Glaze | 721.194 | 0.0733583 | 615.403ms | 4604 | 160 | 3191.43 | 6088.12 | 0.0307882 | 3.41539 | 2(Loss) | true |
