
----
### Marine IK Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier DID NOT CONVERGE | 683.42 | 0.717593 | 9353.93ms | 1834197 | 40 | 1.34938e+10 | 2.55952e+06 | 10.8027 | -(Win) | false |
| simdjson (reflection) | 659.623 | 0.0707705 | 9724.73ms | 1834197 | 40 | 1.40885e+08 | 2.65186e+06 | 0.104287 | 2(Loss) | true |
| Glaze | 537.394 | 0.212953 | 5644.85ms | 1834197 | 80 | 3.84383e+09 | 3.25502e+06 | 0.881568 | 3(Loss) | true |
| simdjson (ondemand) | 523.13 | 0.0958402 | 5767.05ms | 1834197 | 80 | 8.21597e+08 | 3.34377e+06 | 0.270767 | 4(Loss) | true |
| Jsonifier (two-stage) | 500.986 | 1.05542 | 5606.79ms | 1834197 | 40 | 5.43187e+10 | 3.49157e+06 | 0.532554 | 5(Loss) | true |
