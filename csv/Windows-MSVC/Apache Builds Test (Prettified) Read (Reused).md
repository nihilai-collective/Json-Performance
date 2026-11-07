
----
### Apache Builds Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1581.14 | 0.165874 | 9983.95ms | 124597 | 640 | 9.94507e+06 | 75151.2 | 0.102604 | 1.56524 | 1(Win) | true |
| Jsonifier | 1457.64 | 0.0968477 | 5160.63ms | 124597 | 1280 | 7.97822e+06 | 81519 | 0.207057 | 1.69794 | 2(Loss) | true |
| Glaze | 1414.73 | 0.0900064 | 5236.63ms | 124597 | 2560 | 1.46303e+07 | 83991 | 0.229905 | 1.74945 | 3(Loss) | true |
| simdjson (ondemand) | 1362.08 | 0.142419 | 5369.43ms | 124597 | 640 | 9.87923e+06 | 87237.8 | 0.0469484 | 1.8171 | 4(Loss) | true |
