
----
### Marine IK Small Test (Minified) Write Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1436.02 | 0.221908 | 331.395ms | 4918 | 4890 | 256870 | 3266.09 | 0.0681158 | 1.70909 | 1(Win) | true |
| Glaze | 722.659 | 0.4595 | 641.718ms | 4604 | 640 | 498834 | 6075.78 | 0.15196 | 3.41055 | 2(Loss) | true |
