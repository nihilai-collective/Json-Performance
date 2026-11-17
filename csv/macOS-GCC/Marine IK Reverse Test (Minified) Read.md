
----
### Marine IK Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 590.553 | 0.79903 | 9060.76ms | 1834197 | 80 | 4.48115e+10 | 2.96201e+06 | 2.76728 | 1(Win) | true |
| Jsonifier (two-stage) | 541.911 | 0.523106 | 5062.45ms | 1834197 | 80 | 2.2809e+10 | 3.22789e+06 | 1.33717 | 2(Loss) | true |
| simdjson (ondemand) STATISTICAL TIE | 466.548 | 0.757838 | 5748.35ms | 1834197 | 40 | 3.22933e+10 | 3.7493e+06 | 0.339129 | 3(Tie) | true |
| simdjson (reflection) STATISTICAL TIE | 458.121 | 0.556548 | 5653.03ms | 1834197 | 80 | 3.61265e+10 | 3.81826e+06 | 3.07371 | 3(Tie) | true |
| Glaze | 447.047 | 0.701245 | 6050.77ms | 1834197 | 80 | 6.02302e+10 | 3.91284e+06 | 1.06703 | 5(Loss) | true |
