
----
### Marine IK Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 654.431 | 0.683041 | 9189.51ms | 1834197 | 40 | 1.33327e+10 | 2.6729e+06 | 2.21043 | 1(Win) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 543.028 | 1.42309 | 5487.55ms | 1834197 | 30 | 6.30427e+10 | 3.22125e+06 | 0.582562 | 2(Tie) | true |
| simdjson (reflection) STATISTICAL TIE | 538.307 | 0.184853 | 5451.38ms | 1834197 | 40 | 1.44327e+09 | 3.2495e+06 | 0.0534686 | 2(Tie) | true |
| Glaze | 509.006 | 0.604368 | 5650.25ms | 1834197 | 40 | 1.72548e+10 | 3.43656e+06 | 1.60652 | 4(Loss) | true |
| simdjson (ondemand) | 470.594 | 0.222437 | 6168.07ms | 1834197 | 80 | 5.46893e+09 | 3.71706e+06 | 0.721184 | 5(Loss) | true |
