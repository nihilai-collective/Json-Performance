
----
### Marine IK Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1174.74 | 0.293452 | 452.509ms | 4604 | 1280 | 153982 | 3737.59 | 0.0991883 | 2.09305 | 1(Win) | true |
| Jsonifier (two-stage) | 983.657 | 0.10638 | 548.543ms | 4604 | 30 | 676.437 | 4463.67 | 0.0141866 | 2.50096 | 2(Loss) | true |
| Glaze | 789.3 | 0.1106 | 630.243ms | 4604 | 40 | 1514.11 | 5562.8 | 0.135006 | 3.12359 | 3(Loss) | true |
| simdjson (reflection) | 745.816 | 0.192626 | 675.302ms | 4604 | 30 | 3857.98 | 5887.13 | 0.288497 | 3.30457 | 4(Loss) | true |
| simdjson (ondemand) | 571.487 | 0.124198 | 857.512ms | 4604 | 2560 | 233092 | 7682.96 | 0.00745303 | 4.31667 | 5(Loss) | true |
