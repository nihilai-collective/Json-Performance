
----
### Google Maps Response Small Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1993.57 | 0.1172 | 212.423ms | 4390 | 4890 | 29622.9 | 2100.06 | 0.109088 | 1(Win) | true |
| Jsonifier (two-stage) | 1145.39 | 0.0607811 | 394.77ms | 4390 | 80 | 394.863 | 3655.19 | 0.000341979 | 2(Loss) | true |
| Glaze | 1028.34 | 0.195351 | 464.279ms | 4390 | 80 | 5060.29 | 4071.25 | 0.725433 | 3(Loss) | true |
| simdjson (ondemand) | 717.898 | 0.660861 | 609.482ms | 4390 | 320 | 475307 | 5831.79 | 0.26924 | 4(Loss) | true |
