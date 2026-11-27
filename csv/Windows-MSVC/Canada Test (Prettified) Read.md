
----
### Canada Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (stage-1) | 15934.8 | 0.514035 | 8093.95ms | 5373214 | 1280 | 3.49759e+09 | 321578 | 0.533711 | 0.190619 | 1(Win) | true |
| simdjson (stage-1) DID NOT CONVERGE | 12001.4 | 0.441886 | 5458.82ms | 5373214 | 640 | 2.27827e+09 | 426975 | 2.51289 | 0.252997 | -(Loss) | false |
