
----
### Twitter Partial Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 7922.76 | 0.0349814 | 7742.52ms | 631514 | 4890 | 3.45777e+06 | 76016.3 | 0.148661 | 0.383502 | 1(Win) | true |
| Jsonifier | 7905.81 | 0.0846443 | 7791.33ms | 631514 | 640 | 2.66102e+06 | 76179.2 | 0.0244139 | 0.384331 | 2(Loss) | true |
| simdjson (ondemand) | 5360.31 | 0.0626435 | 5823.7ms | 631514 | 640 | 3.17043e+06 | 112355 | 0.0460103 | 0.566907 | 3(Loss) | true |
| Glaze | 3607.41 | 0.0536157 | 8594.96ms | 631514 | 2560 | 2.05116e+07 | 166950 | 0.0205156 | 0.842383 | 4(Loss) | true |
