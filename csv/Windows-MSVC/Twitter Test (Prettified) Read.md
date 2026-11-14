
----
### Twitter Test (Prettified) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 13343.2 | 0.120416 | 4541.71ms | 631514 | 4890 | 1.44452e+07 | 45136 | 0.0256615 | 0.227579 | 1(Win) | true |
| simdjson (stage-1) | 12696.7 | 0.0566059 | 4770.86ms | 631514 | 640 | 461409 | 47434.2 | 0.0398419 | 0.239165 | 2(Loss) | true |
