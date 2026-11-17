
----
### Google Maps Response Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2748.01 | 0.279314 | 963.113ms | 25388 | 4890 | 2.96153e+06 | 8810.69 | 0.2742 | 1(Win) | true |
| Jsonifier (two-stage) | 2391.01 | 0.375047 | 1126.35ms | 25388 | 1280 | 1.84618e+06 | 10126.2 | 0.242345 | 2(Loss) | true |
| simdjson (reflection) | 1723.49 | 0.562934 | 1524.9ms | 25388 | 1280 | 8.00509e+06 | 14048.2 | 0.958691 | 3(Loss) | true |
| Glaze | 1667.68 | 0.259752 | 1582.84ms | 25388 | 2560 | 3.64074e+06 | 14518.3 | 0.811727 | 4(Loss) | true |
| simdjson (ondemand) | 1394.19 | 0.224338 | 1831.15ms | 25388 | 4890 | 7.42218e+06 | 17366.3 | 0.339899 | 5(Loss) | true |
