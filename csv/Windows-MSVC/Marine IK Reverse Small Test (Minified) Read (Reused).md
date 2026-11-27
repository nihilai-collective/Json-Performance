
----
### Marine IK Reverse Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 544.709 | 0.267089 | 972.942ms | 4604 | 2560 | 1.18657e+06 | 8060.66 | 0.266307 | 4.52945 | 1(Win) | true |
| Jsonifier (two-stage) | 517.938 | 0.178677 | 997.006ms | 4604 | 4890 | 1.12192e+06 | 8477.3 | 0.144387 | 4.7642 | 2(Loss) | true |
| Glaze | 169.912 | 0.113572 | 2764.03ms | 4604 | 2560 | 2.20496e+06 | 25841.1 | 0.0799021 | 14.5552 | 3(Loss) | true |
| simdjson (ondemand) | 104.07 | 0.0787156 | 4507ms | 4604 | 4890 | 5.3932e+06 | 42189.9 | 0.25532 | 23.774 | 4(Loss) | true |
