
----
### Canada Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Canada%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1105.56 | 0.429264 | 6751.93ms | 5212421 | 30 | 1.1176e+10 | 4.49633e+06 | 1.91307 | 1(Win) | true |
| simdjson (ondemand) DID NOT CONVERGE | 1069.19 | 0.198009 | 6851.42ms | 5212421 | 80 | 6.78003e+09 | 4.64929e+06 | 5.5618 | -(Loss) | false |
