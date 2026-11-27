
----
### Marine IK Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 756.689 | 0.609418 | 8149.79ms | 1834197 | 80 | 1.58773e+10 | 2.31169e+06 | 0.420481 | 4.01629 | 1(Win) | true |
| Jsonifier (two-stage) | 617.509 | 0.586645 | 9741.25ms | 1834197 | 40 | 1.10463e+10 | 2.83271e+06 | 0.0442548 | 4.92161 | 2(Loss) | true |
| Glaze | 332.106 | 0.377542 | 8480.98ms | 1834197 | 80 | 3.16343e+10 | 5.26707e+06 | 0.929397 | 9.15166 | 3(Loss) | true |
| simdjson (ondemand) | 212.91 | 0.155539 | 6046.5ms | 1834197 | 30 | 4.89893e+09 | 8.21582e+06 | 0.408871 | 14.2755 | 4(Loss) | true |
