
----
### Marine IK Reverse Small Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 873.856 | 0.129076 | 522.883ms | 4604 | 30 | 1261.84 | 5024.53 | 0.0663852 | 2.81777 | 1(Win) | true |
| Jsonifier (two-stage) | 770.361 | 0.115025 | 576.639ms | 4604 | 4890 | 210172 | 5699.56 | 0.0841601 | 3.19881 | 2(Loss) | true |
| Glaze | 704.93 | 0.364949 | 656.306ms | 4604 | 320 | 165345 | 6228.58 | 0.324509 | 3.49748 | 3(Loss) | true |
| simdjson (reflection) | 664.67 | 0.096381 | 660.79ms | 4604 | 4890 | 198221 | 6605.85 | 0.148344 | 3.71017 | 4(Loss) | true |
| simdjson (ondemand) | 565.905 | 0.117208 | 781.317ms | 4604 | 2560 | 211707 | 7758.75 | 0.0622669 | 4.36048 | 5(Loss) | true |
