
----
### Marine IK Reverse Small Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1899.1 | 0.613558 | 235.157ms | 4604 | 1280 | 257571 | 2312 | 0.653145 | 1(Win) | true |
| simdjson (reflection) | 1607.87 | 0.275922 | 296.096ms | 4918 | 2560 | 165838 | 2917 | 0.484443 | 2(Loss) | true |
| Glaze | 1029.14 | 0.232384 | 430.145ms | 4604 | 2560 | 251638 | 4266.4 | 0.00937471 | 3(Loss) | true |
