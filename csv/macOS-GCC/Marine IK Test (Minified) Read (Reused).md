
----
### Marine IK Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 699.222 | 1.33583 | 8862.29ms | 1834197 | 30 | 3.3503e+10 | 2.50167e+06 | 1.11812 | 1(Win) | true |
| Jsonifier (two-stage) | 580.782 | 0.671658 | 5069.31ms | 1834197 | 40 | 1.6369e+10 | 3.01185e+06 | 2.49845 | 2(Loss) | true |
| simdjson (reflection) STATISTICAL TIE | 451.169 | 0.874077 | 6132.76ms | 1834197 | 30 | 3.44535e+10 | 3.87709e+06 | 2.08279 | 3(Tie) | true |
| Glaze STATISTICAL TIE | 449.067 | 1.82935 | 6159.8ms | 1834197 | 30 | 1.5233e+11 | 3.89524e+06 | 1.30404 | 3(Tie) | true |
| simdjson (ondemand) | 393.28 | 0.808138 | 7295.81ms | 1834197 | 40 | 5.16797e+10 | 4.44779e+06 | 1.16478 | 5(Loss) | true |
