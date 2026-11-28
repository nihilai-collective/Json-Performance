
----
### Double Test Read (Reused) Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Double%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Double%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 995.162 | 1.01795 | 173.057ms | 1811 | 2560 | 798989 | 1735.5 | 1.6268 | 1(Win) | true |
| Glaze | 947.085 | 1.08106 | 184.335ms | 1811 | 640 | 248734 | 1823.6 | 0.2407 | 2(Loss) | true |
| simdjson (ondemand) STATISTICAL TIE | 288.335 | 0.242995 | 598.255ms | 1811 | 4890 | 1.03597e+06 | 5989.93 | 0.771493 | 3(Tie) | true |
| simdjson (reflection) STATISTICAL TIE | 286.971 | 0.206238 | 628.317ms | 1811 | 320 | 49300.3 | 6018.4 | 1.94213 | 3(Tie) | true |
