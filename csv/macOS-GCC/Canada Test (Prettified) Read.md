
----
### Canada Test (Prettified) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 6865.33 | 0.906444 | 9574.35ms | 5373214 | 30 | 1.37325e+09 | 746402 | 3.59843 | 1(Win) | true |
| simdjson (stage-1) | 5997.73 | 1.37357 | 5527.1ms | 5373214 | 320 | 4.40702e+10 | 854373 | 0.365575 | 2(Loss) | true |
